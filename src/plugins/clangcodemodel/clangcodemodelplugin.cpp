/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company.  For licensing terms and
** conditions see http://www.qt.io/terms-conditions.  For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, The Qt Company gives you certain additional
** rights.  These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "clangcodemodelplugin.h"

#include "clangconstants.h"
#include "clangprojectsettingspropertiespage.h"

#ifdef WITH_TESTS
#  include "test/clangcodecompletion_test.h"
#endif

#include <cpptools/cppmodelmanager.h>

#include <projectexplorer/projectpanelfactory.h>
#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/session.h>

#include <texteditor/textmark.h>

namespace ClangCodeModel {
namespace Internal {

namespace {

void initializeTextMarks()
{
    TextEditor::TextMark::setCategoryColor(Core::Id(Constants::CLANG_WARNING),
                                           Utils::Theme::ClangCodeModel_Warning_TextMarkColor);
    TextEditor::TextMark::setCategoryColor(Core::Id(Constants::CLANG_ERROR),
                                           Utils::Theme::ClangCodeModel_Error_TextMarkColor);
}

} // anonymous namespace

bool ClangCodeModelPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorMessage)

    // Register widget for project panel
    auto panelFactory = new ProjectExplorer::ProjectPanelFactory();
    panelFactory->setPriority(60);
    panelFactory->setDisplayName(ClangProjectSettingsWidget::tr("Clang Settings"));
    panelFactory->setSimpleCreateWidgetFunction<ClangProjectSettingsWidget>(QIcon());
    ProjectExplorer::ProjectPanelFactory::registerFactory(panelFactory);

    // Register ModelManagerSupportProvider
    auto cppModelManager = CppTools::CppModelManager::instance();
    cppModelManager->setClangModelManagerSupportProvider(&m_modelManagerSupportProvider);

    initializeTextMarks();

    return true;
}

void ClangCodeModelPlugin::extensionsInitialized()
{
}

#ifdef WITH_TESTS
QList<QObject *> ClangCodeModelPlugin::createTestObjects() const
{
    return {
        new Tests::ClangCodeCompletionTest,
    };
}
#endif


} // namespace Internal
} // namespace Clang